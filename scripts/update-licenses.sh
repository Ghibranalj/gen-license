#!/usr/bin/env sh


LICENSES="agpl-3.0 apache-2.0 bsd-2-clause bsd-3-clause bsd-4-clause bsl-1.0 cc0-1.0 epl-2.0 gpl-2.0 gpl-3.0 lgpl-2.1 lgpl-3.0 mit mpl-2.0 unlicense"

for license in $LICENSES; do
    # remove dash
    # remove zero
    # remove trailing dot
    # change dot to underscore
    licensename=$(echo "$license" | sed -e 's/-//g' -e 's/0//g' -e 's/\.$//' -e 's/\./_/g' -e 's/clause//g' )
    echo Downloading $license from github

    curl -s https://api.github.com/licenses/$license | jq -r '.body' > licenses/$licensename.txt
done
