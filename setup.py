from distutils.core import setup
import setuptools
import sys

module = setuptools.Extension(
    'bitmap',
    sources=['./src/cbitmap/module/bitmap.c'],
    extra_compile_args={"win32": []}.get(sys.platform, ["-Werror", "-std=c99"]),
    extra_link_args={"win32": []}.get(sys.platform, ["-lpthread"])
)


setup(
    name="cbitmap",
    author="dwpeng",
    author_email="1732889554@qq.com",
    url="https://github.com/dwpeng/bitmap",
    description="A C-based bitmap implementation.",
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    version="0.0.1",
    packages=setuptools.find_packages("src"),
    package_dir={"": "src"},
    ext_modules=[module],
    python_requires=">=3.6"
)
