
import svgwrite
from svgwrite import cm, mm   
import cairosvg

def create_a4_svg_with_duplicates(input_svg_path, output_svg_path, img_width, img_height, spacing=2):
    # Constants for A4 paper size in mm
    # a4_width = 210 * mm
    # a4_height = 297 * mm
    a4_width = 210 
    a4_height = 297

    
    # Create a new SVG drawing
    dwg = svgwrite.Drawing(output_svg_path, size=('210mm', '297mm'))
    
    # Calculate how many images fit horizontally and vertically
    num_horizontal = int((a4_width - spacing) / (img_width + spacing))
    num_vertical = int((a4_height - spacing) / (img_height + spacing))
    
    # Load the original SVG content
    with open(input_svg_path, 'r') as file:
        svg_content = file.read().strip()
    
    # Insert duplicates
    for x in range(num_horizontal):
        for y in range(num_vertical):
            x_offset = x * (img_width + spacing)
            y_offset = y * (img_height + spacing)
            # Embed the original SVG as a group
            group = dwg.add(dwg.g())
            group.translate(x_offset, y_offset)
            # group.scale(1)  # Scale if necessary
            group.add(dwg.image(input_svg_path, insert=(0, 0), size=(img_width*mm, img_height*mm)))
    
    # Save the new SVG
    dwg.save()

# Example usage
create_a4_svg_with_duplicates('front.svg', 'output.svg', 100, 55)
cairosvg.svg2pdf(url='output.svg', write_to='output.pdf')
