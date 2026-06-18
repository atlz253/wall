FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive
ARG VCPKG_COMMIT=2025.04.09

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        cmake \
        curl \
        git \
        mingw-w64 \
        ninja-build \
        pkg-config \
        unzip \
        zip \
    && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://packages.microsoft.com/config/ubuntu/24.04/packages-microsoft-prod.deb -o /tmp/packages-microsoft-prod.deb \
    && dpkg -i /tmp/packages-microsoft-prod.deb \
    && rm /tmp/packages-microsoft-prod.deb \
    && apt-get update \
    && apt-get install -y --no-install-recommends powershell \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/microsoft/vcpkg.git /opt/vcpkg \
    && cd /opt/vcpkg \
    && git checkout "${VCPKG_COMMIT}" \
    && ./bootstrap-vcpkg.sh -disableMetrics \
    && /opt/vcpkg/vcpkg install \
        sdl2:x64-mingw-dynamic \
        sdl2-image:x64-mingw-dynamic \
        sdl2-ttf:x64-mingw-dynamic \
    --clean-after-build

COPY cmake/mingw-w64-x64.cmake /opt/toolchains/mingw-w64-x64.cmake

ENV VCPKG_ROOT=/opt/vcpkg
ENV VCPKG_DEFAULT_TRIPLET=x64-mingw-dynamic
ENV VCPKG_DEFAULT_HOST_TRIPLET=x64-linux

WORKDIR /src

ENTRYPOINT ["bash", "/src/scripts/build-windows.sh"]
