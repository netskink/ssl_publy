
INFILE=$1
OUTFILE="${INFILE%.*}.der"

openssl x509 -in ${INFILE} -outform der -out ${OUTFILE}

