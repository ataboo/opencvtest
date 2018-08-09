# Project to Learn OpenCV's Object Recognition

## Getting Samples

### Get Negatives
1. Search [Image Net](http://image-net.org/) to find sample negative background images.
2. Add the urls to `neg/moneran-urls.txt`
3. Build `importimgs.cpp`
  - `g++ main.cpp -o importimgs `pkg-config --cflags --libs opencv -lcurl`
4. Run to populate neg with sized grayscale versions or those that work
5. `bg_mon.lst` will be populated with these negative images which will be the `-bg` arg for a few commands

### Get Positives
1. Crop a few positive images with a solid black background and put them in `samples`
2. Tweak and run `python make_samples.py -i samples` to save them as separate vectors in samples
    - bg_color should be black (0) and bgthresh low (1) for a black background
3. Combine the samples using `python mergevec.py -v samples -o combined.vec` into combined.vec

## Train the Cascade
```
opencv_traincascade -data data -vec combined.vec -bg bg_mon.lst -numPos 1800 -numNeg 180 -numStages 10 -w 32 -h 32
```

- data: output cascade in the data folder
- vec: the combined vector to use.  Good to keep this in the root dir
- bg: the background (neg) list file.  This breaks if it's in the neg dir
- numPos: number of positive images
- numNeg: number of negative images
- numStages: number of stages to run
- w: width should match vector?
- h: height should match vector?

## Run the Match
1. Build with "g++ detect.cpp -o detect `pkg-config --cflags --libs opencv`"
2. Run ./detect
3. Tweak scale value, neighbours