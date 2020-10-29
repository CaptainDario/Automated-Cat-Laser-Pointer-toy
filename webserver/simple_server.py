####################################################
# This script should be run in:
#   .\laser_pointer_toy\webserver
# otherwise it will most probably fail or not work correctly.
####################################################


import http.server 
import socketserver
import os

PORT = 8000

os.chdir(os.path.join("..", "data"))

Handler = http.server.SimpleHTTPRequestHandler

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print("serving at port", PORT)
    httpd.serve_forever()