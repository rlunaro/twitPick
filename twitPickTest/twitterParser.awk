#
# twitterParser.awk
#


BEGIN   {
}

    {
    if( match( $0, /^      "id_str":[[:space:]]*"([0-9]*)"/, aParsed ) )
        print "id: " aParsed[1];
    }


    