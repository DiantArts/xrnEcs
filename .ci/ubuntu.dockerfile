FROM ubuntu:latest

ARG CXX_PACKAGE
ARG CXX

ENV CXX ${CXX}
ENV XRN_MAKEFILE_USE_COVERAGE true
ENV XRN_MAKEFILE_ERRORFILE false
ENV DEBIAN_FRONTEND noninteractive

WORKDIR /usr/src/ubuntuSourceCode
COPY . /usr/src/ubuntuSourceCode

# Base packoges
RUN true \
    && apt-get -y update \
    && apt-get install -y build-essential software-properties-common \
    && add-apt-repository -y ppa:ubuntu-toolchain-r/test \
    && apt-get install -y ${CXX_PACKAGE} git wget python-dev autotools-dev libicu-dev libbz2-dev make gcovr valgrind \
    && rm -rf /var/lib/apt/lists/*

# Boost 1.78
RUN true \
    && cd /home \
    && wget http://downloads.sourceforge.net/project/boost/boost/1.78.0/boost_1_78_0.tar.gz \
    && tar xfz boost_1_78_0.tar.gz \
    && rm boost_1_78_0.tar.gz \
    && cd boost_1_78_0/ \
    && mkdir /usr/src/ubuntuSourceCode/externs/HdrOnly/boost \
    && cp -R ./boost /usr/src/ubuntuSourceCode/externs/HdrOnly/ \
    && cd .. \
    && rm -rf boost_1_78_0/

# Compilations and tests
RUN make
RUN make tests
CMD [ "sh", "-c", "make auto_tests" ]
