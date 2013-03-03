    class OpenGLMatrixHelper
    {
    public:
        OpenGLMatrixHelper( GLuint uniform_matrix_id ):_uniform_matrix_id( uniform_matrix_id )
        {
            // スタックのデフォルト基底階層に単位行列をロードしておく
            _matrix_stack.push( glm::mat4(1.0) );
        }
        // matrix support
        void LoadMatrix( const glm::mat4& mat )
        {
            _matrix_stack.top() = mat;
            // モデルマトリックス送信
            glUniformMatrix4fv( _uniform_matrix_id, 1, 0,
                               glm::value_ptr( _matrix_stack.top() ) );
            return;
        }
        void MultMatrix( const glm::mat4& mat )
        {
            _matrix_stack.top() *= mat;
            // モデルマトリックス送信
            glUniformMatrix4fv( _uniform_matrix_id, 1, 0,
                               glm::value_ptr( _matrix_stack.top() ) );
            return;
        }
        void PushMatrix( void )
        {
            _matrix_stack.push( _matrix_stack.top() );
            return;
        }
        void PopMatrix( void )
        {
            _matrix_stack.pop();
            // モデルマトリックス送信
            glUniformMatrix4fv( _uniform_matrix_id, 1, 0,
                               glm::value_ptr( _matrix_stack.top() ) );
        }
    public:
        GLuint _uniform_matrix_id;
        std::stack< glm::mat4 > _matrix_stack;
    };

