import zeep

wsdl_url = "http://www.dneonline.com/calculator.asmx?WSDL"
soap = zeep.Client(wsdl=wsdl_url) 

result = soap.service.Add(5, 5)
print("5 + 5 = ", result)

result = soap.service.Multiply(5, 5)
print("5 * 5 = ", result)

