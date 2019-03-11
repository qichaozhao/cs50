from flask import Flask

app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Set the root_dir
app.config["ROOT_DIR"] = "/Users/qzhao/cs50/qichaozhao"

# Import our libraries
import sys
sys.path.append(f"{app.config['ROOT_DIR']}")

from py_sorts import insertion_sort, selection_sort, bubble_sort, \
    merge_sort_nr, quick_sort_ip, radix_sort, bucket_sort
from c_sorts import wrapper
c_sorts = wrapper.c_sorts()

# Import our views
import webapp.routes