import zeep

wsdl_url = "http://localhost:8000/?wsdl"
soap = zeep.Client(wsdl=wsdl_url)

result = soap.service.add(5, 5)
print("5 + 5 = ", result)
