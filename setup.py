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
    version="1.0",
    description="c version bitmap",
    author="dwpeng",
    packages=setuptools.find_packages("src"),
    package_dir={"": "src"},
    ext_modules=[module],
    classifiers=[
        "Development Status :: 4 - Beta",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: Apache Software License",
        "Operating System :: MacOS",
        "Operating System :: POSIX :: Linux",
        "Operating System :: Microsoft :: Windows",
        "Topic :: Software Development :: Quality Assurance",
        "Topic :: Software Development :: Bug Tracking",
        "Topic :: System :: Logging"
    ],
    python_requires=">=3.6"
)
