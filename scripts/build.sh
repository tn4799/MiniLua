#!/usr/bin/env bash
set -ev

pushd build
make $@
popd

