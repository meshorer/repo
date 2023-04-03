gpg --encrypt -r dani@gmail.com -o enc.gpg copy1.txt

gpg --sign --compress-level 9 --output signed_file2.gpg copy2.txt       

gpg --detach-sign --output myfile4.sig copy4.txt 


