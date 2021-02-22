package de.hechler.calliope;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class CalliopeHexPatcher {

	private final static String DEFAULT_SEARCH_PATTERN = "5465537454655874";
	private final static String DEFAULT_INPUT_FILENAME = "input/base.hex";
	private final static String DEFAULT_OUTPUT_FILENAME = "input/patched-base.hex";
	private final static String DEFAULT_REPLACEMENT_TEXT = "{\"params\":[{\"input_layer_size\":6},{\"output_layer_size\":3},{\"activation\":\"relu\",\"hidden_layer_sizes\":[5,5]}],\"coefs\":[[[-0.1774340,1.7180027,-2.2185390,-2.7157181,-1.8493312],[-0.2929120,-0.2159229,-0.1926039,0.4891134,0.5775759],[0.3595690,0.3887749,-0.0562094,-0.1737957,-0.5248434],[0.1492369,-0.4726848,0.5037789,-1.0239458,-0.8647448],[0.8280657,0.3250253,0.2636314,0.3337166,0.5085575],[-0.3032101,-0.0393003,-0.0539968,0.1071070,0.0712103]],[[-1.0918019,-0.3682515,-0.0070016,0.6161266,-4.7436538e-316],[1.1717495,1.3598602,-0.9327373,1.0735065,7.3903137e-316],[1.2006478,1.9328969,0.3707930,-3.3001615,-4.36019e-317],[-3.2961095,1.5889390,2.5617188,0.9860016,-1.0129486e-315],[2.6647761,-1.7936426,0.0199456,-0.8790681,4.6865165e-316]],[[1.9443124,-8.0195728,1.0388437],[3.7354118,-5.1001390,1.8261879],[-3.0452043,0.2562118,1.1356915],[-1.5016578,0.6879718,1.6212931],[-3.2343488e-315,3.8369143e-315,-3.0680620e-315]]],\"intercepts\":[[0.5143649,0.3070222,1.0359252,1.3399955,1.2130860],[-0.0479019,-1.8792909,1.7528952,-0.0097069,-0.6972091],[1.4335063,4.5834377,-3.2468793]]}";
	
	public static void main(String[] args) throws IOException {
		String searchPattern = DEFAULT_SEARCH_PATTERN;
		String inputFilename = DEFAULT_INPUT_FILENAME;
		String outputFilename = DEFAULT_OUTPUT_FILENAME;
		String replacementText = DEFAULT_REPLACEMENT_TEXT;
		Scanner scanner = new Scanner(new File(inputFilename));
		FileWriter out = new FileWriter(outputFilename);
		String previousLine = null;
		while (scanner.hasNext()) {
			String line = scanner.nextLine();
			if (line.contains(searchPattern)) {
				startOverwrite(out, previousLine, line, scanner, replacementText);
				previousLine = null;
				line = scanner.nextLine();
			}
			if (previousLine != null) {
				out.write(previousLine+"\r\n");
			}
			previousLine = line;
		}
		if (previousLine != null) {
			out.write(previousLine+"\r\n");
		}
		out.close();
	}

	
	
	private static void startOverwrite(FileWriter out, String previousLine, String line, Scanner scanner, String replacementText) {
		if (replacementText.length()<33) {
			replacementText += "                                 ".substring(replacementText.length());
		}
		replaceText(out, previousLine, replacementText);
		replacementText = replacementText.substring(16);
		replaceText(out, line, replacementText);
		while (replacementText.length()>16) {
			replacementText = replacementText.substring(16);
			line = scanner.nextLine();
			replaceText(out, line, replacementText);
		}
		if (!line.substring(9, 41).equals("20202020202020202020202020202020")) {
			throw new RuntimeException("replacementText too long!");
		}
	}



	private static void replaceText(FileWriter out, String line, String replacementText) {
		try {
			String start = line.substring(0, 9);
			int chk = 0;
			for (int i=0; i<4; i++) {
				int b = Integer.parseInt(start.substring(1+2*i, 3+2*i), 16); 
				chk += b;
			}
			String replace = "";
			for (int i=0; i<16; i++) {
				if (i == 16) {
					break;
				}
				int c = (replacementText+"                ").charAt(i);
				chk += c;
				String hx = c2hx(c);
				replace += hx;
			}
			String check = c2hx(-chk);
			out.write(start+replace+check+"\r\n");
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		
	}



	private static String c2hx(int c) {
		String hx = Integer.toHexString(c & 0xFF);
		if (hx.length()<2) {
			hx = "0"+hx;
		}
		return hx;
	}

}
