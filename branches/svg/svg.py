"""''''''''''''''''''''''''''''''''''
SVG to robot converter by Jordan Perr (neutrino15).

--Team 694 (Stuypulse)--
--http://stuypulse.com--

Language: Python
Platforms: Tested on Mac/Linux/Windows with Python 2.5 (Should work on just about anything)
Lisence: You are free do whatever you want with this. Just say something like "Based off of Jordan Perr's SVG Converter."

Scans an svg file (tiny1.0 or 1.1 works best, but any standard svg will work)
for any paths with an id prefixed with "robopath-"
As of now, a path like "test robopath-default" would work. The ID would end up being "default"
This enables you to export multiple paths to your robot.
The order of paths will be based upon the order they appear in your SVG file. It will print the name of the path and the order number for your reference.

For example:
	if your SVG contains two paths, robopath_2 and robopath_42, the robot would have something like
	path[0] = robopath_2
	path[1] = robopath_42
	
Below are some settings you may want to change. You probably don't need to change these.
''''''''''''''''''''''''''''''''''"""
##Print more
debug = 1

##Fairly standard for most vector editors, 72 pixels per inch.
##Only edit if the Field Dimensions are very wrong in the output.
pixels_in_inch = 72


"""''''''''''''''''''''''''''''''''"""

import re, os, string, sys, xml.dom.minidom

print("\n")
print("SVG Export by Jordan Perr, Team 694 (Stuypulse).")
print("Read the included comments if you are having problems.")
print("Version 0.2\n")

if (len(sys.argv) == 1):
	print "ERROR: You must input the path to a valid SVG file as the 1st argument."
	print "Example: python svg.py path_to_file.svg\n"
	sys.exit()

svgPath = os.path.join(sys.path[0], sys.argv[1])
print "Trying to open %s.\n" % (svgPath)

doc = xml.dom.minidom.parse(svgPath)
svg = doc.getElementsByTagName('svg')
svg = svg[0]

paths = svg.getElementsByTagName('path')

i = 0
robopaths = []
for potentialPath in paths:
	if (potentialPath.attributes.keys().count("id") == 1):
		if(potentialPath.attributes["id"].value.find("robotpath-")):
			potentialPath.attributes["id"].value = potentialPath.attributes["id"].value.split("robopath-")[1]
			robopaths.append(potentialPath)
			

		
if (len(robopaths) == 0):
	print "ERROR: I don't see any paths named with prefix \"robopath_\""
	sys.exit()

numb = re.compile("[0-9]+(\.[0-9]+)?") #Either an integer or a decimal must be >= 1px

fieldWidth = float(numb.search(svg.attributes["width"].value).group())
fieldHeight = float(numb.search(svg.attributes["height"].value).group())

print "\nSuccess! Found %d path(s) prefixed with \"robopath-\"" % (len(robopaths))
print "Field Dimensions w=%f  h=%f" % (fieldWidth/pixels_in_inch, fieldHeight/pixels_in_inch)

j = 0
output = "@" + str(fieldWidth) + "," + str(fieldHeight) + "$"

for i in robopaths:
	print "[%d] %s ==> %s" % (j, i.attributes["id"].value, i.attributes["d"].value.replace(' ', ''))
	output = output + i.attributes["d"].value.replace(' ', '') + "$"
	j = j+1

output = output + "#"

if debug:
	print "\nDEBUG- The following will be exported via serial:"
	print output

print "\n"
