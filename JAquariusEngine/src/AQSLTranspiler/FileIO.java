package AQSLTranspiler;

import javax.swing.*;
import javax.swing.filechooser.FileFilter;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.*;
import java.util.Arrays;

public class FileIO {
    public String readFileReturnStr(String fileName) {
        try{
            File file = new File(fileName);
            FileReader fileReader = new FileReader(file);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            String readText = "";
            String strBuffer;
            while ((strBuffer = bufferedReader.readLine()) != null){
                readText = readText + strBuffer + "\n";
            }
            return readText;
        } catch (NullPointerException | FileNotFoundException exception){
            System.out.println(exception.getMessage());
        } catch (IOException ioException) {
            ioException.printStackTrace();
        }
        return null;
    }
    public void saveTextAsGLSL(String text, String[] fileTypeDescriptions , String[] fileExtensions){
        JFileChooser fileChooser = new JFileChooser();
        for (int i = 0; i < fileTypeDescriptions.length; i++){
            fileChooser.addChoosableFileFilter(new FileNameExtensionFilter(fileTypeDescriptions[i], fileExtensions[i]));
        }
        FileFilter[] filters = fileChooser.getChoosableFileFilters();
        fileChooser.setFileFilter(filters[1]);
        int dialog = fileChooser.showOpenDialog(null);
        if (dialog == JFileChooser.APPROVE_OPTION){

            File file = getSelectedFileWithExtension(fileChooser);

            try{
                FileWriter fileWriter = new FileWriter(file, false);
                BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
                bufferedWriter.write(text);

                bufferedWriter.flush();
                bufferedWriter.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
    public void saveTextAsCPPHeader(String text, String fileTypeDescription , String fileExtension){

    }

    /**
     * Returns the selected file from a JFileChooser, including the extension from
     * the file filter.
     */
    public File getSelectedFileWithExtension(JFileChooser c) {
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
}
