#!/bin/bash

# Config
BASE_DIR="docs/ui/exports"
SLIDER="$BASE_DIR/gain_slider.png"
TMP_DIR="$BASE_DIR/frames"
TARGET_FRAMES=128

# Parallel arrays for background → output
BACKGROUND_FILES=("input_gain.png" "output_gain.png")
OUTPUT_FILES=("input_gain_filmstrip.png" "output_gain_filmstrip.png")

# Ensure ImageMagick is available
command -v magick >/dev/null 2>&1 || {
  echo >&2 "ImageMagick 'magick' not found. Install it first."
  exit 1
}

# Get slider dimensions
IDENTIFY_OUTPUT=$(magick identify -format "%w %h" "$SLIDER")
SLIDER_WIDTH=$(echo "$IDENTIFY_OUTPUT" | awk '{print $1}')
SLIDER_HEIGHT=$(echo "$IDENTIFY_OUTPUT" | awk '{print $2}')

if [[ -z "$SLIDER_WIDTH" || -z "$SLIDER_HEIGHT" ]]; then
  echo "Failed to get dimensions of $SLIDER"
  exit 1
fi

# Calculate step size for smooth animation
STEP_SIZE=$(((SLIDER_HEIGHT) / TARGET_FRAMES))

echo "Slider size: ${SLIDER_WIDTH}x${SLIDER_HEIGHT}, step size: ${STEP_SIZE}px"

# Loop over each background image
for i in "${!BACKGROUND_FILES[@]}"; do
  BG_FILE="${BACKGROUND_FILES[$i]}"
  OUTPUT_FILE="${OUTPUT_FILES[$i]}"
  BG_PATH="$BASE_DIR/$BG_FILE"
  OUTPUT="$BASE_DIR/$OUTPUT_FILE"

  echo "Generating filmstrip for $BG_FILE → $OUTPUT"

  # Get background dimensions
  BG_IDENTIFY=$(magick identify -format "%w %h" "$BG_PATH")
  BG_WIDTH=$(echo "$BG_IDENTIFY" | awk '{print $1}')
  BG_HEIGHT=$(echo "$BG_IDENTIFY" | awk '{print $2}')

  # Prepare temp directory
  rm -rf "$TMP_DIR"
  mkdir -p "$TMP_DIR"

  for ((frame = 0; frame < TARGET_FRAMES; frame++)); do
    PADDED=$(printf "%03d" "$frame")
    OUTPUT_FRAME="$TMP_DIR/frame_$PADDED.png"

    # Calculate Y position for slider (moving from bottom to top)
    # Frame 0: slider at bottom, Frame 127: slider at top
    Y_POSITION=$((BG_HEIGHT - SLIDER_HEIGHT - (frame * STEP_SIZE)))

    # Composite slider onto background at calculated position
    # Use precise geometry and disable any filtering/resampling
    magick "$BG_PATH" "$SLIDER" \
      -filter point \
      -interpolate integer \
      -geometry "+0+${Y_POSITION}" \
      -composite \
      -strip \
      "$OUTPUT_FRAME"
  done

  # Combine all frames into vertical filmstrip with no compression/filtering
  echo "Combining frames into vertical filmstrip..."
  magick "$TMP_DIR"/frame_*.png \
    -filter point \
    -append \
    -strip \
    "$OUTPUT"

  echo "Filmstrip created: $OUTPUT"
done

# Final cleanup
rm -rf "$TMP_DIR"

echo "All filmstrips generated successfully."