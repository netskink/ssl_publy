

od -t x1 -An  $1 | awk '

{

    for (i = 1; i <= 16; i++)
        printf "0x%s,", $i
    print ""
}
'

