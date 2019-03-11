from flask import render_template, request

from webapp import app
from webapp import c_sorts
from webapp import insertion_sort, selection_sort, bubble_sort, bucket_sort, radix_sort, quick_sort_ip, \
    merge_sort_nr

import random
import time
import json

# Global variable containing the sorting algorithms available and the keys
PY_SORTS = {
    "insertion": insertion_sort,
    "selection": selection_sort,
    "bubble": bubble_sort,
    "bucket": bucket_sort,
    "radix": radix_sort,
    "quick": quick_sort_ip,
    "merge": merge_sort_nr,
}

C_SORTS = {
    "insertion": c_sorts.insertion_sort,
    "selection": c_sorts.selection_sort,
    "bubble": c_sorts.bubble_sort,
    "merge": c_sorts.merge_sort,
    "quick": c_sorts.quick_sort,
    "radix": c_sorts.radix_sort,
    "bucket": c_sorts.bucket_sort
}


#
# Ensure responses aren't cached
#
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@app.route("/index")
def index():
    """Return the main page"""

    # Make lists of available py_sorts and c_sorts
    py_sorts_avail = [(k, "{} Sort".format(k.capitalize())) for k in sorted(PY_SORTS.keys())]
    c_sorts_avail = [(k, "{} Sort".format(k.capitalize())) for k in sorted(C_SORTS.keys())]
    return render_template('index.html', py_sorts_avail=py_sorts_avail, c_sorts_avail=c_sorts_avail)


@app.route("/compare", methods=["POST"])
def compare():
    """
    Get the lists of algorithms to run, run them for our pre-defined set of inputs and return the results in a set of tables for plotting.

    :return:
    """

    # Get the selected comparisons from the user response
    py_selected = request.form.getlist("py_sort_select")
    c_selected = request.form.getlist("c_sort_select")

    # Keep the test arrays shorter if we have selected the On2 algos
    if len({"insertion", "selection", "bubble"}.intersection(set(py_selected + c_selected))) > 0:
        max_rng = 5
    else:
        max_rng = 11

    # Here we setup our test arrays and randomize them
    arr_lens = sorted([5000 * x for x in range(1, max_rng)])
    arrs = [random.sample(list(range(l)), l) for l in arr_lens]

    res = []
    for sort in py_selected:
        res.append({
            "name": f"py_{sort}",
            "data": [[l, runner(PY_SORTS[sort], arr.copy(), mode="time")] for (l, arr) in zip(arr_lens, arrs)]
        })

    for sort in c_selected:
        res.append({
            "name": f"c_{sort}",
            "data": [[l, runner(C_SORTS[sort], arr.copy(), mode="time")] for (l, arr) in zip(arr_lens, arrs)]
        })

    return render_template("results_multi.html", py_selected=py_selected, c_selected=c_selected, res=json.dumps(res),
                           x_axis=json.dumps(arr_lens))


@app.route("/run", methods=["GET", "POST"])
def run_one():
    """
    Run one algorithm and return the results as well as the time taken
    :return:
    """

    if request.method == "GET":
        # Make lists of available py_sorts and c_sorts
        py_sorts_avail = [(k, "{} Sort".format(k.capitalize())) for k in sorted(PY_SORTS.keys())]
        c_sorts_avail = [(k, "{} Sort".format(k.capitalize())) for k in sorted(C_SORTS.keys())]
        return render_template("run.html", py_sorts_avail=py_sorts_avail, c_sorts_avail=c_sorts_avail)

    else:
        # Here we get our algorithm and the input array
        algo_type = request.form.get("algo_type", "")
        input_arr_str = request.form.get("input_arr", [])
        input_arr = [int(s.strip()) for s in input_arr_str.split(",")]

        if algo_type == "c":
            algo_name = request.form.get("c_sort_select")
            alg = C_SORTS[algo_name]
        else:
            algo_name = request.form.get("py_sort_select")
            alg = PY_SORTS[algo_name]

        arr, t = runner(alg, input_arr, mode="sort_time")

        return render_template("results.html", algo_type=algo_type.capitalize(), algo_name=algo_name.capitalize(),
                               input_arr=", ".join(map(str, input_arr[:25])),
                               sorted_arr=", ".join(map(str, arr[:25])), time_elapsed=t)


def runner(sortf, arr, mode="sort"):
    """
    A wrapper which returns either the sorted array or returns the time it took to sort the array.

    :param sortf:
    :param arr:
    :param mode:
    :return:
    """

    tss = time.time()
    arr = sortf(arr)
    tse = time.time()

    if mode == "sort":
        return arr
    elif mode == "time":
        return tse - tss
    elif mode == "sort_time":
        return arr, tse - tss
    else:
        raise ValueError("Invalid mode sent for sort (must be one of { time, sort }")
