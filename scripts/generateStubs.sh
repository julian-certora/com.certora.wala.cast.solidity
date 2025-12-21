#!/bin/bash

for type in `cat $1`; do
    cat <<EOF
bool Translator::visit(const $type &_node) {
    return visitNode(_node);
}

EOF
done
