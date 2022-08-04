#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include <stdbool.h>

typedef struct Bitmap {
  uint64_t size;
  uint64_t ele_size;
  uint8_t buff[];
} Bitmap;

Bitmap *create_bitmap(uint64_t size) {
  uint64_t real_size = size / 8 + 1;
  Bitmap *b = calloc(1, sizeof(Bitmap) + sizeof(uint8_t) * real_size);
  b->size = real_size;
  b->ele_size = size;
  return b;
}

void print_bitmap(Bitmap *b) {
  uint64_t size = b->size;
  uint64_t i, j;
  for (i = 0; i < size / 10; i++) {
    printf("%ld: ", i);
    for (j = 0; j < 10; j++) {
      printf("%d\t", b->buff[i * 10 + j]);
    }
    printf("\n");
  }

  uint64_t start = (i + 1) * 10;
  if (start == size)
    return;
  for (; start < size; start++) {
    printf("%d ", b->buff[start]);
  }
  printf("\n");
}

bool get(Bitmap *b, uint64_t n) {
  uint64_t offset = n % 8;
  uint64_t count = n / 8;
  if (count >= b->size)
    return false;
  uint8_t offset_number = (1 << offset);
  if ((b->buff[count] & offset_number) == offset_number) {
    return true;
  }
  return false;
}

void set(Bitmap *b, uint64_t n) {
  uint64_t offset = n % 8;
  uint64_t count = n / 8;
  b->buff[count] = b->buff[count] | (1 << offset);
}

void free_bitmap(Bitmap *b) {
  if (b) {
    free(b);
  }
}

void dumps(Bitmap *b, char *path) {
  FILE *fp = fopen(path, "wb");
  fwrite(&b->size, sizeof(uint64_t), 1, fp);
  fwrite(&b->ele_size, sizeof(uint64_t), 1, fp);
  fwrite(b->buff, sizeof(uint8_t), b->size, fp);
  fclose(fp);
}

Bitmap *loads(char *path) {
  uint64_t size = 0, ele_size = 0;
  FILE *fp = fopen(path, "rb");
  fread(&size, sizeof(uint64_t), 1, fp);
  fread(&ele_size, sizeof(uint64_t), 1, fp);
  Bitmap *b = create_bitmap(ele_size);
  fread(b->buff, sizeof(uint8_t), size, fp);
  fclose(fp);
  return b;
}

// Python api
PyObject *create(PyObject *self, PyObject *args) {
  uint64_t size = 0;
  if (!PyArg_ParseTuple(args, "l", &size)) {
    Py_RETURN_NONE;
  }
  if (!size)
    Py_RETURN_NONE;
  Bitmap *b = create_bitmap(size);
  return PyLong_FromVoidPtr(b);
}

PyObject *load(PyObject *self, PyObject *args) {
  char *path = NULL;
  if (!PyArg_ParseTuple(args, "s", &path)) {
    Py_RETURN_NONE;
  }
  Bitmap *b = loads(path);
  return PyLong_FromVoidPtr(b);
}

PyObject *dump(PyObject *self, PyObject *args) {
  void *b = NULL;
  char *path = NULL;
  if (!(PyArg_ParseTuple(args, "ls", &b, &path))) {
    Py_RETURN_NONE;
  }
  dumps((Bitmap *)b, path);
  Py_RETURN_TRUE;
}

PyObject *destory(PyObject *self, PyObject *args) {
  void *ptr = NULL;
  if (!PyArg_ParseTuple(args, "l", &ptr)) {
    Py_RETURN_NONE;
  }
  free_bitmap((Bitmap *)ptr);
  Py_RETURN_NONE;
}

PyObject *len(PyObject *self, PyObject *args) {
  void *ptr = NULL;
  if (!PyArg_ParseTuple(args, "l", &ptr)) {
    Py_RETURN_NONE;
  }
  uint64_t ele_size = ((Bitmap *)ptr)->ele_size;
  return PyLong_FromUnsignedLong(ele_size);
}

PyObject *get_number(PyObject *self, PyObject *args) {
  void *ptr = NULL;
  uint64_t n = 0;
  if (!PyArg_ParseTuple(args, "ll", &ptr, &n)) {
    Py_RETURN_FALSE;
  }
  if (get((Bitmap *)ptr, n)) {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

PyObject *set_number(PyObject *self, PyObject *args) {
  void *ptr = NULL;
  uint64_t n = 0;
  if (!PyArg_ParseTuple(args, "ll", &ptr, &n)) {
    Py_RETURN_FALSE;
  }
  set((Bitmap *)ptr, n);
  Py_RETURN_TRUE;
}

static PyMethodDef Methods[] = {
    {"create", create, METH_VARARGS, "create a bitmap"},
    {"load", load, METH_VARARGS, "load a bitmap"},
    {"dump", dump, METH_VARARGS, "dump a bitmap"},
    {"destory", destory, METH_VARARGS, "destory a bitmap"},
    {"len", len, METH_VARARGS, "the length of a bitmap"},
    {"get", get_number, METH_VARARGS, "get a number from bitmap"},
    {"set", set_number, METH_VARARGS, "set a number to bitmap"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef module = {PyModuleDef_HEAD_INIT, "bitmap",
                                    "A c version bitmap", -1, Methods};

PyMODINIT_FUNC PyInit_bitmap(void) { return PyModule_Create(&module); }
