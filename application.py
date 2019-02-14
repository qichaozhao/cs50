import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["POST"])
def post_form():

    # Get all the form arguments
    fname = request.form.get("firstname", "")
    lname = request.form.get("lastname", "")
    email = request.form.get("email", "")
    food = request.form.get("food", "")
    pwd = request.form.get("pwd", "")
    special = 1 if request.form.get("is_special", False) else 0

    # Make some error checking
    if "" in (fname, lname, email, food, pwd) or special == 0:
        return render_template("error.html", message="The form was not filled out completely! Please try again.")

    # Append to CSV
    with open('survey.csv', 'a') as f_out:
        writer = csv.writer(f_out)
        writer.writerow([fname, lname, email, food, pwd, special])

    return redirect('/sheet', code=302)


@app.route("/sheet", methods=["GET"])
def get_sheet():

    columns = ["First Name", "Last Name", "E-Mail", "Food", "Password", "Special"]
    # Read the written CSV file
    with open('survey.csv', 'r') as f_in:
        reader = csv.DictReader(f_in, fieldnames=columns)
        rows = [r for r in reader]

    return render_template("responses.html", rows=rows, cols=columns)
