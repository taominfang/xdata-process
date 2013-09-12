
1. get all help information

./xdata-process --help

./xdata-process -H

2. do the unit test

./xdata-process -U

--unit_test   -U 


3. regular search and replace:

[ Debug]$ ./xdata-process --awk_search_reg '(\d+)([a-z]+)' -i /tmp/reg_replace_sample.txt 
[awk_search_reg]=(\d+)([a-z]+)
[input_file]=/tmp/reg_replace_sample.txt
<Whole string>[123456abcd]<$1$>[123456]<$2$>[abcd]
<Whole string>[2345689add]<$1$>[2345689]<$2$>[add]
<Whole string>[123abcdd]<$1$>[123]<$2$>[abcdd]
<Whole string>[89aabbc]<$1$>[89]<$2$>[aabbc]
[ Debug]$ ./xdata-process --awk_search_reg '(\d+)([a-z]+)' -i /tmp/reg_replace_sample.txt --awk_out_formater '$1$  eee $2$\n'
[awk_out_formater]=$1$  eee $2$\n
[awk_search_reg]=(\d+)([a-z]+)
[input_file]=/tmp/reg_replace_sample.txt
test:$1$  eee $2$\n
123456  eee abcd
2345689  eee add
123  eee abcdd
89  eee aabbc

