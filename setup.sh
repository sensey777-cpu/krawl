#!/data/data/com.termux/files/usr/bin/bash
echo "Installing Krawl Language v3.5..."
g++ krawl.cpp -o krawl
cp krawl $PREFIX/bin/
chmod +x $PREFIX/bin/krawl
echo "Done! Now you can type 'krawl' anywhere."
