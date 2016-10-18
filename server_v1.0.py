#pip import pyown
#pip import praw

from time import gmtime, strftime
import pyowm
import praw

WEATHER_API_KEY = "d3041fa4dec2792d29c137b03e0f5bd0"
WEATHER_LOC = "Champaign, IL"

REDDIT_CLIENT = "Bthp4CLVJkNwOw"
REDDIT_SECRET = "vv24h5SBYahhn-L-_hApDFQvCKk"
REDDIT_USER = "python:SmartMirrorServer:v1.0 (by /u/JamMore)"
SUBREDDIT = "news"


def getDateTime():
    return strftime("%Y-%m-%d %H:%M", gmtime()) 

def getWeather():
    owm = pyowm.OWM(WEATHER_API_KEY)
    observation = owm.weather_at_place(WEATHER_LOC)
    w = observation.get_weather()
    return [w.get_status(), w.get_temperature('fahrenheit')]

def getHeadlines():
    r = praw.Reddit(client_id=REDDIT_CLIENT, user_agent=REDDIT_USER, client_secret=REDDIT_SECRET)
    submissions = r.get_subreddit(SUBREDDIT).get_hot(limit=5)
    return [str(x) for x in submissions] 

def getInfo(): 
    info = {}
    info['DateTime'] = getDateTime()
    info['Weather'] = getWeather()
    info['Headlines'] = getHeadlines()
    return info

def server(): 
    print getInfo()

server()
