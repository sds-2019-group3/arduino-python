sURL = "http://sds.samchatfield.com/api/room/%s" % roomID
data = { "wifiSpeed" : downspeed()*8 }
request = requests.put(sURL, json=data )
request.raise_for_status()