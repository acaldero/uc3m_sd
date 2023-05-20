
import zeep

# prepara el cliente soap
wsdl_url = "http://localhost:8000/?wsdl"
soap = zeep.Client(wsdl=wsdl_url)

# Usa la API
result = soap.service.add(5, 5)
print("5 + 5 = ", result)

result = soap.service.sub(5, 5)
print("5 - 5 = ", result)

result = soap.service.inc(1)
print("inc(1) = ", result)

