#
# Dockerfile for Neo64 development
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

# Use ubuntu 24.04 (jammy)
FROM ubuntu:24.04

# Make sure we're totally up to date
RUN apt update -y
RUN apt upgrade -y

# Install sudo
RUN apt install -y sudo

# Set up the container to not need a password to run `sudo`
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

# Non-Root user arguments
ARG USERNAME=ultra64
ARG USER_UID=1001
ARG USER_GID=$USER_UID

ENV DEBIAN_FRONTEND=noninteractive \
    PYTHONBUFFERED=1

RUN apt install -y build-essential \
                   python3-full \
                   python3-pip \
                   python-is-python3 \
                   doxygen \
                   tar \
                   git \
                   bash-completion \
                   clang-tidy-19 \
                   clang-format-19 \
                   sudo \
                   vim \
                   && apt clean \
                   && rm -rf /var/lib/apt

# Add a non-root user that has sudo access
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# Set the default user to be our non-root user
USER $USERNAME

ENTRYPOINT ["/bin/bash"]
