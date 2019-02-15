import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Get the user and holding details
    usr = db.execute("SELECT * FROM users WHERE id = :uid", uid=session['user_id'])
    holdings = db.execute("SELECT symbol, sum(quantity) as quantity FROM transactions WHERE user_id = :uid GROUP BY symbol HAVING sum(quantity) > 0",
        uid=session['user_id'])

    # Loop through the list and for each symbol dict append the price returned through lookup
    for h in holdings:
        q = lookup(h['symbol'])
        h['latest_price'] = q['price']
        h['name'] = q['name']
        h['total'] = q['price'] * h['quantity']

    return render_template('index.html', holdings=holdings, cash=round(usr[0]['cash'], 2))


@app.route("/deposit", methods=["POST"])
@login_required
def deposit():
    """Deposit more cash"""

    dep = float(request.form.get("cash", "0"))
    db.execute("UPDATE users SET cash = cash + :dep WHERE id = :uid",
        dep=dep, uid=session['user_id'])

    return redirect('/')


@app.route("/withdraw", methods=["POST"])
@login_required
def withdraw():
    """Withdraw existing cash"""

    withdraw = float(request.form.get("cash", "0"))
    usr = db.execute("SELECT cash FROM users where id = :uid", uid=session['user_id'])

    if usr[0]['cash'] < withdraw:
        return apology("Cannot withdraw more than you have in the account")

    db.execute("UPDATE users set cash = cash - :withdraw WHERE id = :uid",
        withdraw=withdraw, uid=session['user_id'])

    return redirect('/')


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")

    elif request.method == "POST":

        symbol = request.form.get("symbol", "")
        shares = int(request.form.get("shares", "0"))

        # Validate the input
        if shares <= 0:
            return apology("You're trying to buy an invalid number of stocks, what's wrong with you?")

        q = lookup(symbol)
        if q is None:
            return apology("Invalid symbol entered. Cannot buy.")

        # Check the user cannot buy more than the money they have left
        acct = db.execute("SELECT cash FROM users where id = :uid", uid=session['user_id'])
        cash = acct[0]["cash"]
        if q['price'] * shares > cash:
            return apology("You do not have that much money available in your account.")

        # Make the transaction into the database
        db.execute("INSERT INTO transactions ('user_id', 'symbol', 'price', 'quantity') VALUES (:uid, :symbol, :price, :qty)",
            uid=session['user_id'], symbol=symbol, price=q['price'], qty=shares)

        # Update the users cash balance
        new_balance = cash - q['price'] * shares
        db.execute("UPDATE users SET cash = :cash WHERE id = :uid", uid=session['user_id'], cash=new_balance)

        return redirect('/')

    return apology("Something unexpected went wrong!")


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""

    uname = request.args.get("username", "")
    usrs = db.execute("SELECT * FROM users WHERE username = :uname", uname=uname)

    if len(uname) > 1 and len(usrs) == 0:
        return jsonify({"status": "valid"}), 200
    else:
        return jsonify({"status": "invalid"}), 400


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT * FROM transactions WHERE user_id = :uid", uid=session['user_id'])

    # Append the type
    for t in transactions:
        t['type'] = 'Buy' if t['quantity'] > 0 else 'Sell'
        t['quantity'] = abs(t['quantity'])
        # t['created_on'] = t['created_on'].strftime('%y-%m-%d %H:%M:%S')
        t['total'] = t['quantity'] * t['price']

    return render_template('history.html', transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template('quote.html')

    elif request.method == "POST":
        q = lookup(request.form.get("symbol", ""))
        if q is None:
            return apology("The symbol you input could not be found")

        return render_template('quoted.html', symbol=q['symbol'], name=q['name'], price=q['price'], ts=datetime.utcnow().strftime('%Y-%m-%d %H:%M:%S'))

    return apology("Sorry, something unexpected went wrong!")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template('register.html')

    elif request.method == "POST":

        # Check the submitted registration info
        uname = request.form.get("username", "")
        pwd = request.form.get("password", "")
        pwd_conf = request.form.get("confirmation", "")

        if "" in (uname, pwd, pwd_conf):
            return apology("Please ensure all fields are filled out!")

        if pwd != pwd_conf:
            return apology("Provided passwords do not match. Please provide matching password and confirmation.")

        usrs = db.execute("SELECT * FROM users WHERE username = :uname", uname=uname)
        if len(usrs) == 1:
            return apology("Your username already exists, please choose a different username")

        # All validation checks passed so we can insert the new user
        db.execute("INSERT INTO users ('username', 'hash') VALUES (:uname, :pwd_hash)", uname=uname, pwd_hash=generate_password_hash(pwd))
        return redirect('/', 302)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    holdings = db.execute("SELECT symbol, sum(quantity) as quantity FROM transactions WHERE user_id = :uid GROUP BY symbol HAVING sum(quantity) > 0",
        uid=session['user_id'])

    if request.method == "GET":
        return render_template("sell.html", holdings=holdings)

    elif request.method == "POST":

        symbol = request.form.get("symbol", "")
        shares = int(request.form.get("shares", "0"))

        # Validate the input
        if shares <= 0:
            return apology("You're trying to sell an invalid number of stocks, what's wrong with you?")

        q = lookup(symbol)
        if q is None:
            return apology("Invalid symbol entered. Cannot sell.")

        # Check the user cannot sell more than the shares they have left
        holding = list(filter(lambda h: h['symbol'] == symbol, holdings))
        if shares > holding[0]['quantity']:
            return apology(f"You do not have that many shares of {symbol} to sell.")

        # Make the transaction into the database
        db.execute("INSERT INTO transactions ('user_id', 'symbol', 'price', 'quantity') VALUES (:uid, :symbol, :price, :qty)", 
            uid=session['user_id'], symbol=symbol, price=q['price'], qty=-shares)

        # Update the users cash balance
        acct = db.execute("SELECT cash FROM users where id = :uid", uid=session['user_id'])
        cash = acct[0]["cash"]
        new_balance = cash + q['price'] * shares
        db.execute("UPDATE users SET cash = :cash WHERE id = :uid", uid=session['user_id'], cash=new_balance)

        return redirect('/')

    return apology("Something unexpected went wrong!")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
