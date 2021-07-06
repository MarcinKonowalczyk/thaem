# Run `source ../../gif_script.fish` in ./build_osx/frames/

# Convert from hacky png to actuall png and flip upside down (aka the right way round)
# for f in *.png;
#     echo $f;
#     convert -flip $f "conv_$f" && rm $f && mv "conv_$f" $f;
# end

# Delete the first frame if it exists
# [ -f "00000.png" ] && rm "00000.png";

# Make a gif with imagemagick
convert -delay 3 -flip -verbose *.png +dither "output_dither.gif"

# compress gif
gifsicle -O1 --loopcount forever output_dither.gif -o output_web.gif