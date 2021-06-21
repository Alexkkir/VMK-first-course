import urllib.request
import base64


url = r"https://vk.com/doc194035965_594623492"
file_path = r"C:\Users\1\Documents\EVM\2_semester\Preparation_to_linal"

request = urllib.Request(url)
base64string = base64.b64encode('%s:%s' % ("alexkkir", "Akir232002vk"))
request.add_header("Authorization", "Basic %s" % base64string)
result = urllib.urlopen(request)

filename = "pdf_3"
response = urllib.request.urlopen(url)
file = open(file_path + "\\" + filename + ".pdf", 'wb')
file.write(response.read())
file.close()
