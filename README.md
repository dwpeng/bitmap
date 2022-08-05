# cbitmap
A C-based bitmap implementation.

## Install
```sh
pip install cbitmap
```

## Basic Usage

### import
```python
from cbitmap import Bitmap
```

### init a bitmap

```python
# pass a number to init a bitmap
size = 100
b = Bitmap(size)

# or load a bitmap from disk
path = '/path/data'
b = Bitmap.load(path)
```

### set
```python
b = Bitmap(100)
b.set(10)
```

### get
```python
b = Bitmap(100)
b.set(10)
print(b.get(10))  # True
print(b.get(1))   # False
print(b.get(100000)) # False
```

### delete
```python
b = Bitmap(100)
b.set(10)
print(b.get(10))  # True
b.delete(10)
print(b.get(10))  # False
```

### Persistence

```python
b = Bitmap(1000)
path = '/path/data'
b.dump(path)
```

```python
b = Bitmap.load(path)
len(b) == 1000  # True
```
