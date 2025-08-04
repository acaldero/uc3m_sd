
all:
	python3 ./lib-server.py &
	python -mzeep http://localhost:8000/?wsdl
	python3 ./app-d.py

install:
	pip install zeep spyne

clean:
	rm -fr __pycache__

