# -*- coding: utf-8 -*-
from __future__ import print_function
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials
from googleapiclient.http import MediaIoBaseDownload
import csv
import re
import requests
import shutil
import io
# specify input CSV here
input_file = r"C:\Users\1\Documents\EVM\2_semester\Preparation_to_linal_2\tirtish_kollok4.csv"
# specify output directory here
output_dir = r"C:\Users\1\Documents\EVM\2_semester\Preparation_to_linal_2\tirtish_kollok4.csvtkt_coll4_out"
links_column = 0
# If modifying these scopes, delete the file token.json.
SCOPES = ['https://www.googleapis.com/auth/drive']


def main():
    """Shows basic usage of the Drive v3 API.
    Prints the names and ids of the first 10 files the user has access to.
    """
    creds = None
    # The file token.json stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    if os.path.exists('token.json'):
        creds = Credentials.from_authorized_user_file('token.json', SCOPES)
    # If there are no (valid) credentials available, let the user log in.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                r'C:\Users\1\Documents\EVM\2_semester\Preparation_to_linal_2\credentials.json', SCOPES)  # specify credentials file here
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open('token.json', 'w') as token:
            token.write(creds.to_json())

    drive_service = build()('drive', 'v3', credentials=API_KEY)
    with open(input_file, 'r') as csvfile:
        csv_tkt = csv.reader(csvfile, delimiter=';')
        first_row = next(csv_tkt)
        for row in csv_tkt:
            # print(row)
            user_name = row[0].replace(' ', '_')
            # print(user_name)
            link = row[1]
            download_id = re.search('/d/(.*)/', link).group(1)
            name_request = drive_service.files().get(fileId=download_id, fields='name').execute()
            # print(name_request['name'])
            request = drive_service.files().get_media(fileId=download_id)
            # print(request.execute())
            fh = io.BytesIO()
            downloader = MediaIoBaseDownload(fh, request)
            done = False
            while done is False:
                status, done = downloader.next_chunk()
            fh.seek(0)
            with open(output_dir + u'\\' + name_request['name'] + user_name.decode('cp1251') + '.pdf', 'wb') as f:
                shutil.copyfileobj(fh, f)


if __name__ == '__main__':
    main()
