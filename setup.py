import setuptools
from Cython.Build import cythonize

module = setuptools.Extension(
    'bitmap',
    [
        './src/cbitmap/module/ccbitmap.pyx', 
    ],
)

__version__ = '0.0.2'

setuptools.setup(
    name="cbitmap",
    author="dwpeng",
    author_email="1732889554@qq.com",
    url="https://github.com/dwpeng/bitmap",
    description="A C-based bitmap implementation.",
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    version=__version__,
    packages=setuptools.find_packages("src"),
    package_dir={"": "src"},
    ext_modules=cythonize([module]),
    python_requires=">=3.6"
)
