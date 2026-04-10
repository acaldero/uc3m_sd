import rpyc
from rpyc.utils.server import ThreadedServer

class CalculatorService(rpyc.Service):
   def exposed_add(self, a, b):
       return a + b
   def exposed_sub(self, a, b):
       return a - b
   def exposed_mul(self, a, b):
       return a * b
   def exposed_div(self, a, b):
       return a / b

if __name__ == "__main__":
   server = ThreadedServer(CalculatorService, port = 12345)
   server.start()

