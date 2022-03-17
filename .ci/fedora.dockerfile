FROM fedora:latest

ARG CXX_PACKAGE
ARG CXX

ENV CXX ${CXX}
ENV XRN_MAKEFILE_USE_COVERAGE true
ENV XRN_MAKEFILE_ERRORFILE false
ENV DEBIAN_FRONTEND noninteractive

WORKDIR /usr/src/fedoraSourceCode
COPY . /usr/src/fedoraSourceCode

# Base packoges
RUN true \
    && dnf update -y \
    && dnf install -y ${CXX_PACKAGE} git wget make findutils gcovr valgrind

# Boost 1.78
RUN true \
    && cd /home \
    && wget http://downloads.sourceforge.net/project/boost/boost/1.78.0/boost_1_78_0.tar.gz \
    && tar xfz boost_1_78_0.tar.gz \
    && rm boost_1_78_0.tar.gz \
    && cd boost_1_78_0/ \
    && mkdir /usr/src/fedoraSourceCode/externs/HdrOnly/boost \
    && cp -R ./boost /usr/src/fedoraSourceCode/externs/HdrOnly/ \
    && cd .. \
    && rm -rf boost_1_78_0/

# Compilations and tests
RUN make
RUN make tests
CMD [ "sh", "-c", "make auto_tests" ]
