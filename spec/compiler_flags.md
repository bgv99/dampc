### Compiler flags
| Flag (full)     | Flag (short)     | Required | Value type | Default value            | Description                |
|-----------------|------------------|----------|------------|--------------------------|----------------------------|
| `--help`        | `-h`             | No       |            |                          | Display help.              |
| `--version`     | `-v`             | No       |            |                          | Show the version.          |
| `--output`      | `-o`             | No       | String     | out                      | Specify an output file.    |
| `--input`       | `-i`             | Yes      | String     |                          | Specify an input file.     |
| `--optimise`    | `-opt`           | No       | Boolean    | false                    | Choose to optimise or not. |
| `--edition`     | `-e`             | No       | Integer    | Latest available edition | Specify language edition.  |

Notes:
- `--input` can be used with multiple files.
- `--edition` will use the latest available Damp edition if not specified.
- If the `--output` flag is not specified when compiling, the default name will be 'out'.
