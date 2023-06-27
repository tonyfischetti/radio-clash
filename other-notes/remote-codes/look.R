
# RR

dat <- fread("./remote-codes.tsv")

dat[, .(theremote, address, what), code] -> tmp

tmp[duplicated(code), .(code)][!duplicated(code), code] -> dupes

tmp[code %chin% dupes, ][address=="0x0"]

# duplicates (among NECs with address of 0x0)
# code  elegoo   wide boy
# 0x7   down     music 4
# 0x45  power    B
# 0x44  back     W
# 0x40  play )   On



