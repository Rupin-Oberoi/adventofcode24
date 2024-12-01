import requests
from dotenv import load_dotenv
import os

load_dotenv()

session_key = os.getenv('AOC_SESSION_KEY')
input_dir = 'inputs'

os.makedirs(input_dir, exist_ok=True)

def download_input(day, year=2024):
    url = f"https://adventofcode.com/{year}/day/{day}/input"
    cookies = {'session': session_key}
    response = requests.get(url, cookies=cookies)
    if response.status_code == 200:
        with open(f"{input_dir}/day{day}.txt", "w") as f:
            f.write(response.text)
        print(f"Input for day {day} downloaded successfully")

if __name__ == '__main__':
    DAY = int(input("Enter the day: "))
    download_input(DAY)