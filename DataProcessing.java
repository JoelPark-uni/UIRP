import java.io.*;
import java.util.*;
import java.lang.Integer;

public class FileRead {
	private static File Ratings = new File("/root/project/Web-App/data/ratings.dat");
	private static File Users = new File("/root/project/Web-App/data/users.dat");
	private static File Movies = new File("/root/project/Web-App/data/movies.dat");
	
	private int [] User_Occupation = new int[6041];
	private boolean [][] Movie_Genre = new boolean[3953][18];


	private static String[] occupation_enum = new String[41];
	private static String[] genre_enum = {"Action", "Adventure", "Animation", "Children's", "Comedy", "Crime", "Documentary", "Drama", "Fantasy", "Film-Noir", "Horror", "Musical", "Mystery", "Romance", "Sci-Fi", "Thriller", "War", "Western"};

	public void Sort_UserOccupation() {
		Scanner MyReader = new Scanner(Users);
		while (MyReader.hasNextLine()) {
			String line = MyReader.nextLine();
			String UserID = new String("");
			String occupation = new String("");

			int len = line.length();
			int check = 0; // for checking ':' deliminator

			for (int i = 0; i < len; i++) {
				if (data.charAt(i) == ':') {
					if (data.charAt(++i) == ':') {
						++check;
						continue;
					}
					else {
						// ':' symbol only once >> not a deliminator, just continue
						i--;
						continue;
					}
				}
				else if (check == 0) {
					UserID += line.charAt(i);
				}
				else if (check == 3) {
					occupation += line.charAt(i);
					User_Occupation[Integer.parseInt(UserID)] = Integer.parseInt(occupation);
				}
				else if (check > 3) {
					break;
				}
			}
			User_Occupation[Integer.parseInt(UserID)] = Integer.parseInt(occupation);

		}
	}

	public void Sort_MovieGenre() {
			Scanner MyReader = new Scanner(Movies);
			while (MyReader.hasNextLine()) {
			String line = MyReader.nextLine();
			String MovieID = new String("");
			String genre = new String("");

			int len = line.length();
			int check = 0; // for checking ':' deliminter

			for (int i = 0; i < len; i++) {
				if (data.charAt(i) == ':') {
					if (data.charAt(++i) == ':') {
						++check;
						continue;
					}
					else {
						i--;
						continue;
					}
				}
				else if (check == 0) {
					MovieID += line.charAt(i);
				}
				else if (check == 2) {
					genre += line.charAt(i);
				}
			}
			
			// Removing '|' delimiter from genre
			len = genre.length();
			String tmp = new String("");
			for (int i = 0; i < len; i++) {
				if (genre[i] == '|') {
					Movie_Genre[Integer.parseInt(MovieID)][Code_Genre(tmp)] = true;
				}
			}
			Movie_Genre[Integer.parseInt(MovieID)][Code_Genre(tmp)] = true;
		}	
	}
	
	public int Code_Genre(String arg) {
		for (int i = 0; i < 18; i++) {
			if (genre_enum[i] == arg)
				return i;
		}
	}


	public static void main(String[] args) {
		rating = 0;
		rating_count = 0;
		
		occupation_enum[0] = "other";
		occupation_enum[1] = "";
		occupation_enum[2] = "academic";
		occupation_enum[3] = "educator";
		occupation_enum[4] = "artist";
		occupation_enum[5] = "";
		occupation_enum[6] = "clerical";
		occupation_enum[7] = "admin";
		occupation_enum[8] = "college";
		occupation_enum[9] = "grad student";
		occupation_enum[10] = "customer service";
		occupation_enum[11] = "";
		occupation_enum[12] = "doctor";
		occupation_enum[13] = "health care";
		occupation_enum[14] = "executive";
		occupation_enum[15] = "managerial";
		occupation_enum[16] = "farmer";
		occupation_enum[17] = "";
		occupation_enum[18] = "homemaker";
		occupation_enum[19] = "";
		occupation_enum[20] = "K-12 student";
		occupation_enum[21] = "";
		occupation_enum[22] = "lawyer";
		occupation_enum[23] = "";
		occupation_enum[24] = "programmer";
		occupation_enum[25] = "";
		occupation_enum[26] = "retired";
		occupation_enum[27] = "";
		occupation_enum[28] = "sales";
		occupation_enum[29] = "marketing";
		occupation_enum[30] = "scientist";
		occupation_enum[31] = "";
		occupation_enum[32] = "self-employed";
		occupation_enum[33] = "";
		occupation_enum[34] = "technician";
		occupation_enum[35] = "engineer";
		occupation_enum[36] = "tradesman";
		occupation_enum[37] = "craftsman";
		occupation_enum[38] = "unemployed";
		occupation_enum[39] = "";
		occupation_enum[40] = "writer";

		genre_enum[1] = "Action";
		genre_enum[2] = "Adventure";
		genre_enum[3] = "Children's";
		genre_enum

		System.out.println(occupation_enum[0]);
		String occupation = new String("");
		if (args.length == 2)
			occupation = new String(args[1]);
		System.out.println(occupation);
		int occupation_int = 0;
		for (int i=0; i<41; ++i) {
			if (occupation_enum[i] == occupation) {
				occupation_int = i/2;
				break;
			}
		}
		int size = args[0].length();
		ArrayList<String> genre = new ArrayList<String>();
		String tmp = new String("");
		int check = 1;
		for (int i=0; i<size; ++i) {
			if (args[0].charAt(i) == '|') {
				++check;
				genre.add(tmp);
			}
			else {
				tmp += args[0].charAt(i);
			}
		}
		genre.add(tmp);
		String[] result = new String[check];
		int i = 0;
		for (String temp:genre) {
			result[i++] = temp;
		}
		Occupation(occupation_int);
		Genre(result);
		rating_analysis("");
		System.out.println("the rating average is "+rating/rating_count);
	}
}
