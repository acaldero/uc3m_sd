import time
from spyne import Application, ServiceBase, Integer, Unicode, rpc
from spyne.protocol.soap import Soap11
from spyne.server.wsgi import WsgiApplication
from wsgiref.simple_server import make_server

class Calculadora(ServiceBase):
    @rpc(Integer, Integer, _returns=Integer)
    def add(ctx, a, b):
         return a+b

    @rpc(Integer, Integer, _returns=Integer)
    def sub(ctx, a, b):
         return a-b

application = Application(
  services=[Calculadora],
  tns='http://tests.python-zeep.org/',
  in_protocol=Soap11(validator='lxml'),
  out_protocol=Soap11())
application = WsgiApplication(application)

server = make_server('127.0.0.1', 8000, application)
server.serve_forever()

