echo "Running with O0:"
clang -lm -O0 -o main main.c && ./main

echo ""
echo ""
echo ""
echo "Running with O3:"
clang -lm -O3 -o main main.c && ./main


