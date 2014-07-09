
1. get all help information

./xdata-process --help

./xdata-process -H

2. do the unit test

./xdata-process -U

--unit_test   -U 


3. regular search and replace:

echo '<g:image_link><![CDATA[http://www.kellycodetectors.com/cart/image.php?model=n1219-19009&manufacturer=detectorpro&type=productpage1&file=n1219-19009_1f.jpg]]></g:image_link>' |~/Documents/c_project/xdata-process/Debug/xdata-process --awk_search_reg ".*model=(.*?)&.*" --awk_out_formater 'image_url:$matched_whole_string$\npid:$1$\n\n' -v
[awk_out_formater]=image_url:$matched_whole_string$\npid:$1$\n\n
[awk_search_reg]=.*model=(.*?)&.*
[verbose]=1
out pattern:[image_url:$matched_whole_string$\npid:$1$\n\n]
NO input file, will read from STDIN 
INPUT:<g:image_link><![CDATA[http://www.kellycodetectors.com/cart/image.php?model=n1219-19009&manufacturer=detectorpro&type=productpage1&file=n1219-19009_1f.jpg]]></g:image_link>
find v:[matched_whole_string] replace it to [<g:image_link><![CDATA[http://www.kellycodetectors.com/cart/image.php?model=n1219-19009&manufacturer=detectorpro&type=productpage1&file=n1219-19009_1f.jpg]]></g:image_link>]
image_url:<g:image_link><![CDATA[http://www.kellycodetectors.com/cart/image.php?model=n1219-19009&manufacturer=detectorpro&type=productpage1&file=n1219-19009_1f.jpg]]></g:image_link>
find v:[1] replace it to [n1219-19009]
pid:n1219-19009

Done

