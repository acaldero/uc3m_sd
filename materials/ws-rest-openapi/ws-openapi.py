from fastapi  import FastAPI
from pydantic import BaseModel
import uvicorn

# Item asociado a cada clave
class Item(BaseModel):
    name: str
    weight: float

# {10, {name:'', weight:0.0}, ...
list_kv = {}

# fastAPI
app = FastAPI()

@app.put("/items/{key}")
async def add_item(key: int, item: Item):
    list_kv[key] = item
    return { "key": key, "item": item}

@app.get("/items/{key}")
async def select_item(key: int):
    try:
       item = list_kv[key]
    except:
       item = { '', 0.0 }
    return { "key": key, "item": item }

# Main
if __name__ == "__main__":
   uvicorn.run(app, host="127.0.0.1", port=8000)

