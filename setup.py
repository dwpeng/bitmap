from distutils.core import setup, Extension
import setuptools

module = Extension(
    'bitmap',
    sources=['./src/cbitmap/module/bitmap.c']
)


setup(
    name="cbitmap",
    version="1.0",
    description="c version bitmap",
    author="dwpeng",
    packages=setuptools.find_packages("src"),
    package_dir={"": "src"},
    ext_modules=[module]
)
