#!/bin/bash

for type in `cat $1`; do
    cat <<EOF
    virtual bool visit(const $type &_node) override;
EOF
done
