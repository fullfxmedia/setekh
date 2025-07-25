#!/bin/bash
# Config
BASE_DIR="docs/ui/exports"
INDICATOR="$BASE_DIR/frame_indicator.png"
OUTPUT="$BASE_DIR/filmstrip.png"
TMP_DIR="$BASE_DIR/frames"
FRAMES=("frame_000.png" "frame_001.png" "frame_002.png" "frame_003.png" "frame_004.png" "frame_005.png" "frame_006.png" "frame_007.png" "frame_008.png" "frame_009.png" "frame_010.png" "frame_011.png" "frame_012.png" "frame_013.png" "frame_014.png" "frame_015.png" "frame_016.png" "frame_017.png" "frame_018.png" "frame_019.png" "frame_020.png" "frame_021.png" "frame_022.png" "frame_023.png" "frame_024.png" "frame_025.png" "frame_026.png")
ROTATIONS_PER_FRAME=5
ROTATION_STEP=2

# Ensure ImageMagick is available
command -v magick >/dev/null 2>&1 || { echo >&2 "ImageMagick 'magick' not found. Install it first."; exit 1; }

# Prepare temp directory
rm -rf "$TMP_DIR"
mkdir -p "$TMP_DIR"

# Generate frames with rotated indicator overlay
TARGET_FRAMES=128
ORIGINAL_FRAME_COUNT=$((${#FRAMES[@]} * ROTATIONS_PER_FRAME))

for ((INDEX=0; INDEX<TARGET_FRAMES; INDEX++)); do
    # Calculate which base frame to use
    if [[ $INDEX -lt $ORIGINAL_FRAME_COUNT ]]; then
        # Use corrected logic for frame selection
        if [[ $INDEX -eq 0 ]]; then
            # First frame uses frame_000
            BASE_FRAME="$BASE_DIR/${FRAMES[0]}"
        else
            # Subsequent frames: use each frame for 4 rotations
            # Subtract 1 to account for frame_000 only being used once
            ADJUSTED_INDEX=$((INDEX - 1))
            FRAME_INDEX=$((ADJUSTED_INDEX / ROTATIONS_PER_FRAME + 1))
            BASE_FRAME="$BASE_DIR/${FRAMES[$FRAME_INDEX]}"
        fi
    else
        # Use last frame for remaining frames
        LAST_FRAME_INDEX=$((${#FRAMES[@]} - 1))
        BASE_FRAME="$BASE_DIR/${FRAMES[$LAST_FRAME_INDEX]}"
    fi

    # Check if base frame exists
    if [[ ! -f "$BASE_FRAME" ]]; then
        echo "Warning: Base frame $BASE_FRAME not found, skipping..."
        continue
    fi

    ANGLE=$((INDEX * ROTATION_STEP))
    PADDED=$(printf "%03d" "$INDEX")
    OUTPUT_FRAME="$TMP_DIR/frame_$PADDED.png"

    echo "Creating frame $INDEX: base=$(basename "$BASE_FRAME"), angle=${ANGLE}°"

    # Create rotated indicator
    ROTATED_INDICATOR="$TMP_DIR/indicator_$PADDED.png"
    magick "$INDICATOR" -background none -gravity center -rotate "$ANGLE" "$ROTATED_INDICATOR"

    # Overlay rotated indicator onto base frame
    magick "$BASE_FRAME" "$ROTATED_INDICATOR" -gravity center -composite "$OUTPUT_FRAME"

    # Clean up temporary rotated indicator
    rm "$ROTATED_INDICATOR"
done

# Check if we have any frames to combine
if [[ $INDEX -eq 0 ]]; then
    echo "Error: No frames were generated. Check your base frame files."
    exit 1
fi

# Combine into a vertical filmstrip
echo "Combining $TARGET_FRAMES frames into filmstrip..."
magick "$TMP_DIR"/frame_*.png -append "$OUTPUT"

# Clean up temp directory
rm -rf "$TMP_DIR"

echo "Done! Filmstrip created with $TARGET_FRAMES frames saved as $OUTPUT"
echo "Total rotation range: 0° to $((TARGET_FRAMES * ROTATION_STEP - ROTATION_STEP))°"