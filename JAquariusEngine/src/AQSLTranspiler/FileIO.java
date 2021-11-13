package AQSLTranspiler;

import javax.swing.*;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.*;
import java.util.Arrays;
import java.util.Scanner;

public class FileIO {
    public enum FileTypes{
        GLSL, CPPHEADER
    }
    public String readFileReturnStr(String fileName) {
        try{
            File file = new File(fileName);
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            StringBuilder readText = new StringBuilder();
            String strBuffer;
            while ((strBuffer = bufferedReader.readLine()) != null){
                readText.append(strBuffer).append("\n");
            }
            return readText.toString();
        } catch (NullPointerException | FileNotFoundException exception){
            System.out.println(exception.getMessage());
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
        return null;
    }
    public void saveTextAsFile(String text, String[] fileTypeDescriptions , String[] fileExtensions, FileTypes fileType){
        JFileChooser fileChooser = createFilteredFileChooser(fileTypeDescriptions, fileExtensions);
        int dialog = fileChooser.showOpenDialog(null);
        if (dialog == JFileChooser.APPROVE_OPTION){
            try{
                File file = getSelectedFileWithExtension(fileChooser);
                FileWriter fileWriter = new FileWriter(file, false);
                BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);

                try{
                    switch (fileType) {
                        case GLSL -> {
                            bufferedWriter.write(text);
                        }
                        case CPPHEADER -> {
                            StringBuilder modifiedText = new StringBuilder();
                            String varName = JOptionPane.showInputDialog("Enter variable identifier");
                            modifiedText.append("const char* ").append(varName).append(" {\n");

                            Scanner scanner = new Scanner(text);
                            while (scanner.hasNextLine()){
                                String tempLine = scanner.nextLine();
                                tempLine = "\"" + tempLine + "\\n\"\n";
                                modifiedText.append(tempLine);
                            }
                            modifiedText.append("}");

                            bufferedWriter.write(modifiedText.toString());
                        }
                        default -> throw new IllegalStateException("Unexpected value: " + fileType);
                    }
                    bufferedWriter.flush();
                    bufferedWriter.close();
                }catch (IllegalStateException e){
                    e.printStackTrace();
                }

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Returns the selected file from a JFileChooser, including the extension from
     * the file filter. (Means the file will be set with selected extension name even if user didn't select.)
     */
    private File getSelectedFileWithExtension(JFileChooser c) {
        File file = c.getSelectedFile();
        if (c.getFileFilter() instanceof FileNameExtensionFilter) {
            String[] exts = ((FileNameExtensionFilter)c.getFileFilter()).getExtensions();
            String nameLower = file.getName().toLowerCase();
            for (String ext : exts) { // check if it already has a valid extension
                if (nameLower.endsWith('.' + ext.toLowerCase())) {
                    return file; // if yes, return as-is
                }
            }
            // if not, append the first extension from the selected filter
            file = new File(file.toString() + '.' + exts[0]);
        }
        return file;
    }

    private JFileChooser createFilteredFileChooser(String[] fileTypeDescriptions , String[] fileExtensions){
        JFileChooser fileChooser = new JFileChooser();
        for (int i = 0; i < fileTypeDescriptions.length; i++){
            fileChooser.addChoosableFileFilter(new FileNameExtensionFilter(fileTypeDescriptions[i], fileExtensions[i]));
        }
        FileFilter[] filters = fileChooser.getChoosableFileFilters();
        fileChooser.setFileFilter(filters[1]);
        return fileChooser;
    }
}
