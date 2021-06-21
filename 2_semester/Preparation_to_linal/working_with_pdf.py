import pdfplumber
path_to_file = r"C:\Users\1\Documents\EVM\2_semester\Preparation_to_linal"
filename = r"Bilet_0"

with pdfplumber.open(path_to_file + "\\" + filename + ".pdf") as pdf:
    first_page = pdf.pages[0]
    print(first_page.extract_text())
