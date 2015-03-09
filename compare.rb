#!/usr/bin/env ruby

if ARGV.size < 1
  puts "Usage: #{$PROGRAM_NAME} images"
  exit 1
end

$hints = { opencv: {}, ccv: {} }

def detect(filename, tool)
  output = `#{tool}/fnf-detect #{filename}`.chomp.split("\n")
  $hints[tool][filename] = output
end

def regions(filename, tool)
  $hints[tool][filename].inject('-gravity NorthWest') do |args, line|
    x, y, w, h, t = line.split(' ')
    color = case t
            when 'face'    then 'red'
            when 'profile' then 'yellow'
            else 'blue'
            end
    args + " -region #{w}x#{h}+#{x}+#{y} -bordercolor #{color} -border 4"
  end
end

def generate_images(filename)
  opencv_img = File.join 'out', 'opencv', File.basename(filename)
  ccv_img    = File.join 'out', 'ccv', File.basename(filename)
  sbs_img    = File.join 'out', 'side_by_side', File.basename(filename)
  `convert #{filename} #{regions filename, :opencv} #{opencv_img}`
  `convert #{filename} #{regions filename, :ccv} #{ccv_img}`
  `convert #{opencv_img} #{ccv_img} +append #{sbs_img}`
end

`mkdir -p out/opencv out/ccv out/side_by_side`

puts 'Detecting faces and features with OpenCV'
t = Time.now
ARGV.each do |filename|
  detect filename, :opencv
end
puts "OpenCV: #{Time.now - t}s elapsed"

puts 'Detecting faces and features with ccv'
t = Time.now
ARGV.each do |filename|
  detect filename, :ccv
end
puts "ccv: #{Time.now - t}s elapsed"

puts 'Generating images'
t = Time.now
ARGV.each do |filename|
  generate_images filename
end
puts "Generated images in #{Time.now - t}s"
puts 'You can see the images in out/opencv, out/ccv and out/side_by_side'
puts 'On the side by side images, opencv is on the left and ccv on the right'
