#Server

import Pyro4

@Pyro4.expose
class Calculator(object):
    def add(self,x,y):
        return x + y
    
    def subtract(self,x,y):
        return x - y
    
#Create a Pyro4 daemon
daemon = Pyro4.Daemon()
uri = daemon.register(Calculator)


#Print the URI
print("Server URI:", uri)

#start the server
print("Calculator server started. Press ctrl+C to exit.")

try:
    daemon.requestLoop()

except KeyboardInterrupt:
    print("\n Exixting Calculator server.")

    daemon.shutdown()