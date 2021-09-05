import json

with open(r'C:\Users\1\Documents\EVM\2_semester\contest_analiz_yandex\survey_results.json') as f:
    templates = json.load(f)

frazes = {}
for answer in templates:
    if answer['sex'] == "m":
        fraze = answer['answers'][0]['answer']
        if fraze in frazes:
            frazes[fraze] += 1
        else:
            frazes[fraze] = 1

max = max(frazes.values())
for fraze, count in frazes.items():
    if count == max:
        print(fraze, count)
