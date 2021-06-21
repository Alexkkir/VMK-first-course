import urllib.request
# url_path = r"https://drive.google.com/file/d/14guT8A2jH7tYtTwH4vidm8UMk1x2zLKL/view"
# url = r"https://www.eolss.net/sample-chapters/c15/E6-45-06-03.pdf"
url = r"https://www.eolss.net/sample-chapters/c15/E6-45-06-03.pdf"

file_path = r"C:\Users\1\Documents\EVM\2_semester\Preparation_to_linal"
filename = "pdf_1"


response = urllib.request.urlopen(url)
file = open(file_path + "\\" + filename + ".pdf", 'wb')
file.write(response.read())
file.close()
