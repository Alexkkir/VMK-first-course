import pdfplumber
import urllib
import urllib.request


# url = r"https://www.eolss.net/sample-chapters/c15/E6-45-06-03.pdf"
# url = r"https://vk.com/doc194035965_594623492"
url = r"https://drive.google.com/file/d/14guT8A2jH7tYtTwH4vidm8UMk1x2zLKL/view"

file_path = r"C:\Users\1\Documents\EVM\2_semester\Preparation_to_linal"
filename = "pdf_2"

try:
    response = urllib.request.urlopen(url)
except:
    print("Authent...")
else:
    print("Without auth")


# create a password manager
password_mgr = urllib.request.HTTPPasswordMgrWithDefaultRealm()

# Add the username and password.
# If we knew the realm, we could use it instead of None.
# top_level_url = r"http://example.com/foo/"
password_mgr.add_password(None, url, "89859615393", "Akir232002vk")

handler = urllib.request.HTTPBasicAuthHandler(password_mgr)

# create "opener" (OpenerDirector instance)
opener = urllib.request.build_opener(handler)

# use the opener to fetch a URL
opener.open(url)

# Install the opener.
# Now all calls to urllib.request.urlopen use our opener.
urllib.request.install_opener(opener)

response = urllib.request.urlopen(url)
response = urllib.request.urlopen(url)
response = urllib.request.urlopen(url)
file = open(file_path + "\\" + filename + ".pdf", 'wb')
file.write(response.read())
file.close()
