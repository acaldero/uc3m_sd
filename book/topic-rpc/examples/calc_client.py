import rpyc
conn = rpyc.connect("localhost", 12345)

x = conn.root.add(4,7)
print(x)

x = conn.root.sub(4,7)
print(x)

